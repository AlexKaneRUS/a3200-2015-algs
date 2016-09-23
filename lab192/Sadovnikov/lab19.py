__author__ = 'vmath'

from sys import stdin

if __name__ == "__main__":
    cossack = stdin.readline()
    cossack = cossack[:len(cossack) - 1]

def execute(input):
    matrix = [[0 for x in range(len(input))] for x in range(len(input))]
    new_matrix = [[0 for x in range(len(input))] for x in range(len(input))]
    for j in range(len(input)):
        for i in range(len(input) - 1, -1, -1):
            if j == i:
                matrix[i][j] = 1
                new_matrix[i][j] = (input[i])
            elif j < i:
                matrix[i][j] = 0
                new_matrix[i][j] = ('')
            elif j - i == 1:
                matrix[i][j] = int(input[j] == input[i]) + 1
                if input[j] == input[i]:
                    new_matrix[i][j] = (2 * input[i])
                else:
                    new_matrix[i][j] = (input[i])
            else:
                matrix[i][j] = max(2 * int(input[j] == input[i]) + matrix[i + 1][j - 1], matrix[i][j - 1], matrix[i + 1][j])
                if (matrix[i][j] == 2 * int(input[j] == input[i]) + matrix[i + 1][j - 1]) and (int(input[j] == input[i])):
                    new_matrix[i][j] = (input[i], new_matrix[i + 1][j - 1])
                elif matrix[i][j] == matrix[i][j - 1]:
                    new_matrix[i][j] = ('', new_matrix[i][j - 1])
                else:
                    new_matrix[i][j] = ('', new_matrix[i + 1][j])
    output = ''
    return get(output, new_matrix[0][len(input) - 1])

def get(output, tuple):
    if len(tuple) == 2:
        output = tuple[0] + get(output, tuple[1]) + tuple[0]
        return output
    else:
        return tuple[0]

if __name__ == "__main__":
    print(execute(cossack))
