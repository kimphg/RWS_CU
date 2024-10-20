import configparser

class ModuleConfig:
    def __init__(self, config_file):
        self.config = configparser.ConfigParser()
        self.config.read(config_file)
    
    def __getattr__(self, section):
        # Return a lambda function to access the section keys
        return lambda key: self.config.get(section, key, fallback=None)

# Example Usage
if __name__ == "__main__":
    config = ModuleConfig('config.ini')
    
    # Accessing settings
    video_source = config.settings('video_source')
    
    # Accessing detector info
    model_path = config.detector('model_path')
    confidence_threshold = float(config.detector('confidence_threshold'))
    
    # Accessing tracker info
    tracker_type = config.tracker('type')
    
    # Accessing socket info
    max_package_size = int(config.socket('max_package_size'))
    recv_command_port = int(config.socket('recv_command_port'))
    
    print(f"Video source: {video_source}")
    print(f"Detector model path: {model_path}, Confidence threshold: {confidence_threshold}")
    print(f"Tracker type: {tracker_type}")
    print(f"Max package size: {max_package_size}, Recv command port: {recv_command_port}")