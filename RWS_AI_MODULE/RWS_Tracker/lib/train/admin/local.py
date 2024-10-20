class EnvironmentSettings:
    def __init__(self):
        self.workspace_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker'    # Base directory for saving network checkpoints.
        self.tensorboard_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/tensorboard'    # Directory for tensorboard files.
        self.pretrained_networks = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/pretrained_networks'
        self.lasot_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/lasot'
        self.got10k_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/got10k/train'
        self.got10k_val_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/got10k/val'
        self.lasot_lmdb_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/lasot_lmdb'
        self.got10k_lmdb_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/got10k_lmdb'
        self.trackingnet_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/trackingnet'
        self.trackingnet_lmdb_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/trackingnet_lmdb'
        self.coco_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/coco'
        self.coco_lmdb_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/coco_lmdb'
        self.lvis_dir = ''
        self.sbd_dir = ''
        self.imagenet_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/vid'
        self.imagenet_lmdb_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/vid_lmdb'
        self.imagenetdet_dir = ''
        self.ecssd_dir = ''
        self.hkuis_dir = ''
        self.msra10k_dir = ''
        self.davis_dir = ''
        self.youtubevos_dir = ''
