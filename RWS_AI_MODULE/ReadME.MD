# RWS AI MODULE

## Installation
```
conda env create -f rws_env_cuda113.yaml
conda activate rws

# create default local file for tracker
cd RWS_AI_MODULE/RWS_Tracker/
python tracking/create_default_local_file.py --workspace_dir . --data_dir ./data --save_dir ./output

# run main file
cd ../../
python main.py
```
## Project tree

```
.
├── main.py - main source file
├── models - stores model of tracker, yolo
├── ReadME.MD
├── requirements.txt
├── RWS_Detection - Detection class
├── rws_env_cuda113.yaml - Cuda env file 
├── RWS_Tracker - Tracker class 
├── UI_Test - PyQt5 UI for test interaction between tracker module and UI app
└── videos - Video test files
```