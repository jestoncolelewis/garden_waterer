import time

class Plant:
    def __init__(self, name: str,dl:int) -> None:
        self.name = name
        self.drynessLimit = dl
        self.moistureLevel: int
    
    # getters/setters
    def getName(self) -> str:
        return self.name
    def getMoistureLevel(self) -> int:
        return self.moistureLevel
    def getDrynessLimit(self) -> int:
        return self.drynessLimit
    
    def setMoistureLevel(self, ml) -> None:
        self.moistureLevel = ml
    def setDrynessLimit(self, dl) -> None:
        self.drynessLimit = dl

    # methods
    def waterIfNeeded(self) -> None:
        if self.moistureLevel > self.drynessLimit:
            print("Starting watering")
            # send start command to arduino
            time.sleep(1)
            # send stop command to arduino
            print("Stopped watering")
