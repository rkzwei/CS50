import re
import math


def ask():
    try:
        text = input("Input text: ")
    except ValueError:
        print("How did you manage that?")
    return text

# def debug(text):
 #   words = len(re.findall(r"\w+\'\w+|\w+", text))
  #  sentences = len(re.findall(r'[\.\?!;]+', text))
 #   letters = len(re.findall(r'[a-zA-Z]', text))
   # print(f"{letters} letters \n {words} words \n {sentences} sentences \n")


def index(text):
    # finds all words using \w regex special operator, adds them to a list and returns lenght of list
    words = float(len(re.findall(r"\w+(?:'\w+|-\w+)*", text)))
    # same as words but now searches for only letters
    letters = len(re.findall(r'[a-zA-Z]', text))
    L = (letters / words) * 100\
        # same as above but only looks for end of sentence
    sentences = len(re.findall(r'[\.\?!;]+', text))
    S = (sentences / words) * 100
    grade = round((0.0588 * L) - (0.296 * S) - 15.8)
    #print(grade)
    return (grade)


def evaluator(grade):
    # evaluates according to grade score
    if grade < 1:
        print("Before Grade 1")
    # elif grade == 7:
       # print(f"Grade 8") 
    elif grade >= 1 and grade <= 16:
        # rounds for pretty\
        grade = grade
        print(f"Grade {grade}")
    else:
        print("Grade 16+")


def main():
    # single line calling feels dirty
    foo = ask()
    evaluator(index(foo))
    # debug(foo)


main()