from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from llama_cpp import Llama
from typing import Optional, Dict, List 
from contextlib import asynccontextmanager
import os
import logging
import time

# Logging
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s"
)
logger = logging.getLogger(__name__)

# Model Configuration
MODEL_PATH = "./models/Qwen2.5-1.5B-Instruct-Q4_K_M.gguf"
llm: Optional[Llama] = None

# Modern Lifespan Event Handler (Handles startup and shutdown cleanly)
@asynccontextmanager
async def lifespan(app: FastAPI):
    global llm
    logger.info(f"Loading model from: {MODEL_PATH}")
    try:
        llm = Llama(
            model_path=MODEL_PATH,
            n_gpu_layers=-1,  # Offload all layers to your GTX 1650 GPU for maximum speed
            n_ctx=2048,
            n_batch=512,
            n_threads=4,
            verbose=False,
        )
        logger.info("Model loaded onto VRAM successfully!")
    except Exception as e:
        logger.error(f"Failed to load model during startup: {e}")
        raise e
        
    yield  # Server runs here and serves requests
    
    # Cleanup actions on shutdown
    logger.info("Shutting down FastAPI server... Freeing up GPU resources.")
    if llm:
        del llm

# App Initialization with linked Lifespan handler
app = FastAPI(
    title="VoiceNPC-Backend", 
    description="AI-Powered NPC conversation with the player.",
    version="1.0.0",
    lifespan=lifespan
)

# CORS to reach the server from Unreal Engine
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Request Schema
class ChatRequest(BaseModel):
    prompt: str
    max_tokens: Optional[int] = 40
    temperature: Optional[float] = 0.7

# Response Schema
class ChatResponse(BaseModel):
    response: str
    tokens_used: int
    response_time_ms: float

# Short-term Memory Context Variables
CHAT_HISTORY: List[Dict[str, str]] = []
MAX_HISTORY_DEPTH = 6

# Endpoints
@app.get("/health")
async def health():
    if llm is None:
        raise HTTPException(status_code=503, detail="Model not loaded yet.")
    return {
        "status": "ok",
        "model_loaded": True,
        "version": "1.0.0"
    }

@app.post("/chat", response_model=ChatResponse)
async def chat(request: ChatRequest):
    if llm is None:
        raise HTTPException(status_code=503, detail="Model server uninitialized.")
    
    logger.info("Received payload from Unreal Engine.")
    start = time.time()

    # Clean and extract the data from Unreal's combined string 
    raw_payload = request.prompt.strip()

    if "\nUser:" in raw_payload:
        system_prompt, player_message = raw_payload.split("\nUser:", 1)
    else:
        system_prompt = "You are an NPC character in a video game. Respond in 1-2 sentences."
        player_message = raw_payload

    system_prompt = system_prompt.strip()
    player_message = player_message.strip()

    # Update conversation history
    global CHAT_HISTORY
    CHAT_HISTORY.append({"role": "user", "content": player_message})
    if len(CHAT_HISTORY) > MAX_HISTORY_DEPTH:
        CHAT_HISTORY = CHAT_HISTORY[-MAX_HISTORY_DEPTH:]

    # Construct the structural message history context
    messages = [{"role": "system", "content": system_prompt}] + CHAT_HISTORY

    logger.info(f"Parsed System Prompt: '{system_prompt[:60]}...' | Message: '{player_message}'")

    try:
        result = llm.create_chat_completion(
            messages=messages,
            max_tokens=request.max_tokens,
            temperature=request.temperature,
            min_p=0.05,
            stop=["<|im_start|>", "<|im_end|>", "User:", "NPC:", "\n"],
            repeat_penalty=1.15
        )
    except Exception as e:
        logger.error(f"Inference error encountered: {e}")
        if CHAT_HISTORY:
            CHAT_HISTORY.pop()  # Rollback history context if generation breaks
        raise HTTPException(status_code=500, detail=f"Inference processing failed: {e}")
    
    reply_text = result["choices"][0]["message"]["content"].strip()
    tokens = result["usage"]["total_tokens"]

    # Save Assistant generation back to short-term sliding history context
    CHAT_HISTORY.append({"role": "assistant", "content": reply_text})

    elapsed_ms = (time.time() - start) * 1000
    logger.info(f"Generated reply: '{reply_text}' in {elapsed_ms:.0f}ms")

    return ChatResponse(
        response=reply_text,
        tokens_used=tokens,
        response_time_ms=elapsed_ms
    )

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="127.0.0.1", port=8000)