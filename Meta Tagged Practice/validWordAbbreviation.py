class Solution:
    """
    @param word: a non-empty string
    @param abbr: an abbreviation
    @return: true if string matches with the given abbr or false
    """
    '''
    Input : s = "internationalization", abbr = "i12iz4n"
    Output : true
    '''
    def valid_word_abbreviation(self, word: str, abbr: str) -> bool:
        # write your code here
        word_ptr, abbr_ptr = 0, 0
        while word_ptr < len(word) and abbr_ptr < len(abbr):
            if abbr[abbr_ptr].isdigit():
                if abbr[abbr_ptr] == '0':
                    return False
                temp = 0
                while abbr_ptr < len(abbr) and abbr[abbr_ptr].isdigit():
                    temp = temp * 10 + int(abbr[abbr_ptr])
                    abbr_ptr += 1
                word_ptr += temp
                if word_ptr > len(word):
                    return False
            else:
                if abbr[abbr_ptr] != word[word_ptr]:
                    return False
                word_ptr += 1
                abbr_ptr += 1
        return word_ptr == len(word) and abbr_ptr == len(abbr)
        
