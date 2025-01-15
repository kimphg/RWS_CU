import psutil
import time
import cv2
from pynvml import nvmlInit, nvmlDeviceGetHandleByIndex, nvmlDeviceGetMemoryInfo, nvmlDeviceGetUtilizationRates, nvmlShutdown


current_cam_src : cv2.VideoCapture = None

def set_current_cam_src(cap):
    global current_cam_src
    current_cam_src = cap

def get_system_monitor_data():
    
    # Get initial network stats
    net_io_start = psutil.net_io_counters()
    time.sleep(1)  # Wait for the specified interval
    net_io_end = psutil.net_io_counters()

    # Calculate current send/receive in bytes
    net_sent = net_io_end.bytes_sent - net_io_start.bytes_sent
    net_recv = net_io_end.bytes_recv - net_io_start.bytes_recv
    
    # CPU Usage
    cpu_usage = psutil.cpu_percent(interval=0.5)
    
    # RAM Usage
    ram_info = psutil.virtual_memory()
    ram_usage = ram_info.percent
    
    # Uptime in seconds
    uptime_seconds = int(time.time() - psutil.boot_time())
    
    # Check for camera availability
    camera = 1  # Assume no camera is available
    if current_cam_src is not None:
        if current_cam_src.isOpened():
            camera = 0
    
    # GPU Usage (NVIDIA GPUs)
    gpu_data = ""
    try:
        nvmlInit()
        handle = nvmlDeviceGetHandleByIndex(0)  # Get first GPU
        mem_info = nvmlDeviceGetMemoryInfo(handle)
        utilization = nvmlDeviceGetUtilizationRates(handle)
        gpu_mem_usage = (mem_info.used / mem_info.total) * 100  # GPU memory usage
        gpu_util = utilization.gpu  # GPU utilization
        gpu_data = f",gpu_util:{gpu_util},gpu_mem:{gpu_mem_usage:.2f}"
    except Exception:
        gpu_data = ",gpu_util:NA,gpu_mem:NA"  # Fallback if no GPU is found or error occurs
    finally:
        nvmlShutdown()
    
    # Format and return data
    data = (
        f"camera:{camera},cpu:{cpu_usage},ram:{ram_usage},uptime:{uptime_seconds},"
        f"net_sent:{net_sent},net_recv:{net_recv}"
        f"{gpu_data}"
    )
    return data

if __name__ == "__main__":
    # Example usage
    while True:
        print(get_system_monitor_data())
