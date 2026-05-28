def ft_strlen(obj: str) -> int:
    count = 0
    for _ in obj:
        count += 1
    return count


def in_print(s: str):
    width = 80
    indent = "    "
    line = ""
    current_len = 0
    i = 0

    while i < ft_strlen(s):
        while i < ft_strlen(s) and s[i] == " ":
            i += 1
        if i >= ft_strlen(s):
            break

        start = i
        while i < ft_strlen(s) and s[i] != " ":
            i += 1
        word = s[start:i]
        word_len = ft_strlen(word)

        if current_len == 0:
            line = word
            current_len = word_len
        elif current_len + 1 + word_len <= width:
            line += " " + word
            current_len += 1 + word_len
        else:
            print(line)
            line = indent + word
            current_len = ft_strlen(indent) + word_len

    if current_len > 0:
        print(line)
