from dataclasses import dataclass
@dataclass
class Dish:
    name: str
    type: int
    country: str
    calories: float

    def __init__(self, name, type, country, calories) -> None:
        self.name = name
        self.type = type
        self.country = country
        self.calories = calories

    def __repr__(self):
        return f'{self.name}, {self.calories}'

    def __str__(self):
        return self.__repr__()
