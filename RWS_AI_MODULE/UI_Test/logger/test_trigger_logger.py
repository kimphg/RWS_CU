import logging

# Function to be triggered on every log event
def trigger_function(record):
    # Example action: Print log message (or any other action)
    print(f"Triggered function for log: {record.getMessage()}")

# Define a custom handler that triggers a function
class CustomHandler(logging.Handler):
    def emit(self, record):
        # Call the function here
        trigger_function(record)

# Basic configuration with a file handler
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('rws_module.log')  # Only log to file
    ]
)

# Create a handler for the console output
console_handler = logging.StreamHandler()
console_handler.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
console_handler.setFormatter(formatter)

# Create the main logger
logger = logging.getLogger('rws')
logger.setLevel(logging.DEBUG)
logger.addHandler(console_handler)

# Add the custom handler to trigger a function on every log
custom_handler = CustomHandler()
logger.addHandler(custom_handler)

# Test logging
logger.info("This is an info message.")
logger.debug("This is a debug message.")