
def quesId(str):
    for word in str.split(" "):
        if word.lower() == 'who':
            print 'Who question'
        elif word.lower() == 'how':
            print 'How question'
        elif word.lower() == 'when':
            print 'When question'
        elif word.lower() == 'where':
            print 'Where question'
        elif word.lower() == 'why':
            print 'Why question'
        elif word.lower() == 'what':
            print 'What question'
        elif word.lower() == 'which':
            print 'Which question'
        elif word.lower() == 'whom':
            print 'Whom question'
        elif word.lower() == 'name':
            print 'Name question'

if __name__ == '__main__':
    question = 'Who is going to do the utensils now ?'
    quesId(question)
