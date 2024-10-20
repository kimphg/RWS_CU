from lib.test.evaluation.environment import EnvSettings

def local_env_settings():
    settings = EnvSettings()

    # Set your local paths here.

    settings.davis_dir = ''
    settings.got10k_lmdb_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/got10k_lmdb'
    settings.got10k_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/got10k'
    settings.got_packed_results_path = ''
    settings.got_reports_path = ''
    settings.itb_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/itb'
    settings.lasot_extension_subset_path_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/lasot_extension_subset'
    settings.lasot_lmdb_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/lasot_lmdb'
    settings.lasot_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/lasot'
    settings.network_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/output/test/networks'    # Where tracking networks are stored.
    settings.nfs_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/nfs'
    settings.otb_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/otb'
    settings.prj_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker'
    settings.result_plot_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/output/test/result_plots'
    settings.results_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/output/test/tracking_results'    # Where to store tracking results
    settings.save_dir = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/output'
    settings.segmentation_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/output/test/segmentation_results'
    settings.tc128_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/TC128'
    settings.tn_packed_results_path = ''
    settings.tnl2k_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/tnl2k'
    settings.tpl_path = ''
    settings.trackingnet_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/trackingnet'
    settings.uav_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/uav'
    settings.vot18_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/vot2018'
    settings.vot22_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/vot2022'
    settings.vot_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/RWS_Tracker/data/VOT2019'
    settings.youtubevos_dir = ''

    return settings

