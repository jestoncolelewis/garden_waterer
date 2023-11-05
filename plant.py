import time


class Plant:
    def __init__(self, name: str, dl: int) -> None:
        self.name = name
        self.dryness_limit = dl
        self.moisture_level: int = 0
    
    # getters/setters
    def get_name(self) -> str:
        return self.name

    def get_moisture_level(self) -> int:
        return self.moisture_level

    def get_dryness_limit(self) -> int:
        return self.dryness_limit
    
    def set_moisture_level(self, ml) -> None:
        self.moisture_level = ml

    def set_dryness_limit(self, dl) -> None:
        self.dryness_limit = dl

    # methods
    def water_if_needed(self) -> None:
        if self.moisture_level > self.dryness_limit:
            print("Starting watering")
            # send start command to arduino
            time.sleep(1)
            # send stop command to arduino
            print("Stopped watering")
