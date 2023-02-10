import json

from dish import Dish
from utils import get_interval, search, check_request
from terms import NOT_FOUND


def main():
    with open('./dishes.json', encoding='utf-8') as json_file:
        data = json.load(json_file)

    dishes = {}

    for r in data:
        d = Dish(r.get('name'), r.get('type'), r.get('country'), r.get('calories'))
        item = {r.get('name'): d}
        dishes.update(item)
    choose = 1
    while choose:
        request = input("Введите запрос: ")

        term = check_request(request)
        if (term != NOT_FOUND):
            interval, is_not = get_interval(term)
            print("Блюда будут выведены с калориями на интервале", interval)
            res = search(dishes, interval)
            for dish in res:
                print(dish)
        choose = int(input("\n Задать еще запрос 1 - Да, 0 - Нет: "))

if __name__ == '__main__':
    main()

