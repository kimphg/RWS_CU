import logging
import socket

# default detection ip and port
dest_data_ip = "127.0.0.1" 
dest_data_port = 4000
send_data_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def set_dest_data_address(ip, port):
    global dest_data_ip, dest_data_port
    dest_data_ip = ip
    dest_data_port = port
    
# Function to be triggered on every log event
def send_data_to_controller(record):
    global dest_data_port, dest_data_ip, socket
    # Example action: Print log message (or any other action)
    data = f'TNO,[{record.levelname}] {record.getMessage()}'
    data_to_send = data.encode('utf-8')
    send_data_socket.sendto(data_to_send, (dest_data_ip, dest_data_port))
    
class CustomHandler(logging.Handler):
    def emit(self, record):
        # Call the function here
        send_data_to_controller(record)

# Basic configuration without StreamHandler
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('rws_module.log')  # Only log to file
    ]
)
# Create a handler (console in this case)
console_handler = logging.StreamHandler()
console_handler.setLevel(logging.DEBUG) 

# Create a formatter and set it for the handler
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
console_handler.setFormatter(formatter)
custom_handler = CustomHandler()

# main module logger
# Create a logger
logger = logging.getLogger('rws')
# Set the logging level for the logger
logger.setLevel(logging.DEBUG)
# Add the handler to the logger
logger.addHandler(console_handler)
logger.addHandler(custom_handler)


# detector logger
detector_logger = logging.getLogger('detector')
# Set the logging level for the logger
detector_logger.setLevel(logging.DEBUG)
# Add the handler to the logger
detector_logger.addHandler(console_handler)
detector_logger.addHandler(custom_handler)

# tracker logger
tracker_logger = logging.getLogger('tracker')
# Set the logging level for the logger
tracker_logger.setLevel(logging.DEBUG)
# Add the handler to the logger
tracker_logger.addHandler(console_handler)
tracker_logger.addHandler(custom_handler)