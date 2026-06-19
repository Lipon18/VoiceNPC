import os
from huggingface_hub import hf_hub_download

os.makedirs("./models", exist_ok=True)

print("Starting model downloading from Hugging Face... Please wait.")

model_path = hf_hub_download(
    repo_id="Qwen/Qwen2.5-1.5B-Instruct-GGUF",
    filename="qwen2.5-1.5b-instruct-q4_k_m.gguf",
    local_dir="./models",
    local_dir_use_symlinks=False
)

print(f"\nSuccess! Model downloaded and saved to: {model_path}")