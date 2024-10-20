import logging

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

# main module logger
# Create a logger
logger = logging.getLogger('rws')
# Set the logging level for the logger
logger.setLevel(logging.DEBUG)
# Add the handler to the logger
logger.addHandler(console_handler)


# detector logger
detector_logger = logging.getLogger('detector')
# Set the logging level for the logger
detector_logger.setLevel(logging.DEBUG)
# Add the handler to the logger
detector_logger.addHandler(console_handler)

# tracker logger
tracker_logger = logging.getLogger('tracker')
# Set the logging level for the logger
tracker_logger.setLevel(logging.DEBUG)
# Add the handler to the logger
tracker_logger.addHandler(console_handler)