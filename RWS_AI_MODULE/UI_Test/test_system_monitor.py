import psutil
import time
import cv2
from pynvml import nvmlInit, nvmlDeviceGetHandleByIndex, nvmlDeviceGetMemoryInfo, nvmlDeviceGetUtilizationRates, nvmlShutdown

def get_system_monitor_data(interval=1):
    
    # Get initial network stats
    net_io_start = psutil.net_io_counters()
    time.sleep(interval)  # Wait for the specified interval
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
    # try:
    cap = cv2.VideoCapture(0)  # Try to access the default camera
    if cap.isOpened():
        camera = 0  # Camera is available
        cap.release()
    # except Exception:
        # camera = 1  # Camera unavailable
    
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

# Example usage
print(get_system_monitor_data())
