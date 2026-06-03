def NULL_not_found(object: any) -> int:
#your code here
    if object is None:
        print(f"Nothing: {object} {type(object)}")

    elif isinstance(object, float) and object != object:
        print(f"Cheese: nan {type(object)}")

    elif isinstance(object, int) and object == 0:
        print(f"Zero: {object} {type(object)}")

    elif isinstance(object, str) and object == "":
        print(f"Empty: {type(object)}")

    elif isinstance(object, bool):
        print(f"Fake: {object} {type(object)}")

    else:
        print("Type not Found")
        return 1

    return 0