class Person:
  def __init__(self, name):
    self.__name = name


def main():
   person = Person('Dale')
   print(person.__name)

if __name__=="__main__":
    main()