from cs50 import get_string


def main():  # define the main
    text = get_string("Text: ")
    l = count_letters(text)  # get the letter count
    s = count_sentences(text)  # get the sentence count
    w = count_words(text)  # get the word count

    index = round(0.0588 * (100 * l / w) - 0.296 * (100 * s / w) - 15.8)  # plug into the formula

    if index < 1:  # print out the grade based on the index
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):  # function for counting letters
    letter_count = 0
    for i in range(len(text)):
        if text[i].isalpha() == True:
            letter_count += 1

    return letter_count


def count_sentences(text):  # function for counting sentences
    sentence_count = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            sentence_count += 1

    return sentence_count


def count_words(text):  # function for counting words
    word_count = 0
    for i in range(len(text)):
        if text[i].isspace() == True:
            word_count += 1

    word_count += 1  # add extra for the last word

    return word_count


main()  # run the main