<p align="center">
  <img src="https://img.shields.io/badge/Unreal%20Engine-5.5-0E1128?style=for-the-badge&logo=unrealengine&logoColor=white" />
  <img src="https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Python-3.11.9-3776AB?style=for-the-badge&logo=python&logoColor=white" />
  <img src="https://img.shields.io/badge/FastAPI-Backend-009688?style=for-the-badge&logo=fastapi&logoColor=white" />
</p>

## VoiceNPC

VoiceNPC started as an experiment in real-time conversations with AI-powered NPCs using voice input. During development, it evolved into a simple NPC chat system focused on basic AI-driven interactions inside Unreal Engine.

This project is intentionally lightweight and built entirely from scratch without relying on third-party plugins. The goal was to learn how local LLMs can be integrated into Unreal Engine and used for NPC conversations.

## Screenshots

<h2>Screenshots</h2>

<p align="center">
    <img src="Images/Screenshot 2026-06-20 165312.png" width="45%">
  <img src="Images/Screenshot 2026-06-20 165352.png" width="45%">
</p>

<p align="center">
  <img src="images/Screenshot 2026-06-20 165420.png" width="45%">
  <img src="images/Screenshot 2026-06-20 165503.png" width="45%">
</p>

<p align="center">
  <img src="images/Screenshot 2026-06-20 165600.png" width="45%">
  <img src="images/Screenshot 2026-06-20 165710.png" width="45%">
</p>

## Requirements

## Python

Install FastAPI before running the backend:

```cmd
pip install fastapi
```

##  CUDA Setup

For the best performance, configure llama-cpp-python to use your NVIDIA GPU.

Open cmd and run:

``` cmd
set FORCE_CMAKE=1
set CMAKE_ARGS=-DGGML_CUDA=on

pip install llama-cpp-python --updgrade --force-reinstall --no-cache-dir
```

This rebuilds llama-cpp-python with CUDA support enabled.

##  Verify CUDA Is Working

After starting the backend:

```
pythin main.py
```

You should see a output similar to:

```
ggml_cuda_init: GGML_CUDA_FORCE_MMQ: no 
ggml_cuda_init: found 1 CUDA devices: 
    Device 0: NVIDIA GeForce GTX 1650, compute capability 7.5
```
In my case it's GTX 1650, you may have different.

If CUDA devices are listed, the model is successfully using your GPU.

If CUDA is not detected, the model will run on the CPU, which is significantly slower.

##  Model

The project is currently configured to use:

```
qwen2.5-1.5-instruct-q4_k_m.gguf
```

I selected this model because my development machine only has 4GB of VRAM. It offers a reasonable balance between memory usage and response quality.

If your hardware allows it, you can use a larger or more capable GGUF model. Feel free to replace it with your preferred model.

## Changing the Model

The python download script is currently hardcoded to download the Qwen 2.5 1.5B model.

If you want to use a different model:
    - Download your preferred GGUF model.
    - Update the model path in the project.
    - Modify the download script or directly download the new model and past it into the      models folder.

##  Running the Project

Start the Python backend:

```
python main.py
```

Once the backend is running, launch the Unreal Engine project and begin chatting with two given NPC in the game world.

##  Project Status

This is primarily a learning project and proof of concept.

There are many AI NPC solutions available that:
    - Have better architecture
    - Use more advanced design pattern
    - Use better large models or cloud based models
    - Support richer conversations
    - Offer better performance
    - Include additional features and optimizations

This project goal was to build a simple AI-powered NPC chat system from scratch without replying on any plugins, allowing me to better understand local LLM integration and NPC communication workflows.

## Disclaimer

This codebase is intentionally simple and may not represent production-quality architecture.

Feel free to use it as a starting point, experiment with different GGUF models, improve the implementation, and adapt it to your own projects.

## Questions & Feedback

If you have any questions, suggestions, or run into any issues while using this project, feel free to reach out.

I'd love to see what you build with it and hear your feedback.