# RWS AI MODULE

## TODO
- [x] Limit FPS send to controller (45 Hz)
- [x] Limit image size (Full HD 1920x1080)
- [ ] Add AOI (Area of interest)
- [x] Fix crash video stabilizer when change video source 

## Installation
```
conda env create -f rws_env_cuda113.yaml
conda activate rws

# create default local file for tracker
cd RWS_AI_MODULE/RWS_Tracker/
python tracking/create_default_local_file.py --workspace_dir . --data_dir ./data --save_dir ./output

# run main file
cd ../
python main.py

# to test receive frame data from main program, when running main.py, open a new cmd tab:
cd UI_test
python receiver.py

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

Models can be downloaded from the FTP AI server, please contact the project admin

Models and data dir in FTP AI Server: `/rws/models` and `/rws/videos`