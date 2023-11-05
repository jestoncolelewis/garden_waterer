import time


class Plant:
    def __init__(self, name: str, dl: int) -> None:
        self.name = name
        self.drynessLimit = dl
        self.moistureLevel: int = 0
    
    # getters/setters
    def get_name(self) -> str:
        return self.name

    def get_moisture_level(self) -> int:
        return self.moistureLevel

    def get_dryness_limit(self) -> int:
        return self.drynessLimit
    
    def set_moisture_level(self, ml) -> None:
        self.moistureLevel = ml

    def set_dryness_limit(self, dl) -> None:
        self.drynessLimit = dl

    # methods
    def water_if_needed(self) -> None:
        if self.moistureLevel > self.drynessLimit:
            print("Starting watering")
            # send start command to arduino
            time.sleep(1)
            # send stop command to arduino
            print("Stopped watering")
