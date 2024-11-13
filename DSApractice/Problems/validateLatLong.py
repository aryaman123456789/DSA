import re

def is_valid(pair):
    # Updated regular expression to match valid latitude and longitude pairs
    pattern = r'^\((-?\d{1,2}(?:\.\d+)?),(-?\d{1,3}(?:\.\d+)?)\)$'
    
    match = re.fullmatch(pattern, pair)
    if not match:
        return False
    
    x_str, y_str = match.groups()
    
    # Ensure valid decimal numbers without trailing decimal points
    if (x_str.count('.') > 1 or y_str.count('.') > 1 or
        ('.' in x_str and x_str.split('.')[1] == '') or
        ('.' in y_str and y_str.split('.')[1] == '')):
        return False
    
    # Convert to float and validate range
    try:
        x = float(x_str)
        y = float(y_str)
    except ValueError:
        return False
    
    return -90 <= x <= 90 and -180 <= y <= 180

def funcValidPairs(input_list):
    result = []
    for pair in input_list:
        if is_valid(pair):
            result.append('Valid')
        else:
            result.append('Invalid')
    print(' '.join(result))


# Test case
input_list = ["(90,180)", "(+90,+180)", "(90.,180)", "(90.0,180.1)", "(85S,95W)"]
funcValidPairs(input_list)