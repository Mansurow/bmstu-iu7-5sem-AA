from terms import *


def damLev(str1, str2):
    n = len(str1)
    m = len(str2)

    if n == 0 or m == 0:
        if n != 0:
            return n
        if m != 0:
            return m
        return 0

    change = 0
    if str1[-1] != str2[-1]:
        change += 1

    if n > 1 and m > 1 and str1[-1] == str2[-2] and str1[-2] == str2[-1]:
        res = min(damLev(str1[:n - 1], str2) + 1,
                      damLev(str1, str2[:m - 1]) + 1,
                      damLev(str1[:n - 1], str2[:m - 1]) + change,
                      damLev(str1[:n - 2], str2[:m - 2]) + 1)
    else:
        res = min(damLev(str1[:n - 1], str2) + 1,
                      damLev(str1, str2[:m - 1]) + 1,
                      damLev(str1[:n - 1], str2[:m - 1]) + change)
    return res


def check_request(req):
    request = req.lower().split()
    res = 0

    not_valid = True
    for word in request:
        if damLev(word, "блюдо") < 3:
            not_valid = False
            break

    if not_valid:
        print("В запросе должна идти речь о блюдах")
        return 0

    if "калорийность" not in req and\
        "калорийности" not in req:
        print("В запросе должна идти речь о калорийности блюдах")
        return 0

    res = check_term(req)

    return res


def check_term(req):
    result = NOT_FOUND
    if 'очень некалорийной' in req or\
        'очень некалорийная' in req:
        result = VERY_NOT_CALORIE
    elif 'некалорийная' in req or \
         'некалорийнoй' in req:
        result = NOT_CALORIE
    elif 'малая' in req or \
         'малой' in req:
        result = LOW_CALORIE
    elif 'средняя' in req or \
         'средней' in req:
        result = MEDIUM_CALORIE
    elif 'высокая' in req or \
         'высокой' in req:
        result = HIGH_CALORIE
    elif 'не съем' in req:
        result = NOT_EAT
    elif 'очень не высокая'in req or \
         'очень не высокой' in req:
        result = VERY_NOT_HIGH_CALORIE
    elif 'не очень высокая' in req or \
         'не очень высокой' in req:
        result = NOT_VERY_HIGH_CALORIE
    else:
        print("Речь должна идти о каком-то из термов!")
    return result


# калории на 100 грам блюда
def get_interval(term):
    is_not = False
    interval = []
    if term > 7:
        is_not = True

    if term == VERY_NOT_CALORIE:
        interval = [10, 25]
    elif term == NOT_CALORIE:
        interval = [26, 96]
    elif term == LOW_CALORIE:
        interval = [97, 294]
    elif term == MEDIUM_CALORIE:
        interval = [295, 512]
    elif term == HIGH_CALORIE:
        interval = [513, 954]
    elif term == NOT_EAT:
        interval = [955, 2000]
    elif term == NOT_VERY_HIGH_CALORIE:
        interval = [10, 112]
    elif term == VERY_NOT_HIGH_CALORIE:
        interval = [263, 523]

    return interval, is_not

def search(data, border):
    res = []
    for key in data.keys():
        if data[key].calories >= border[0] and data[key].calories <= border[1]:
            res.append(data[key])
    return res