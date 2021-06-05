def log(a, b):
    """ :returns the logarithm of x to the given base. """
    return ln(a) / ln(b)


def ln(b):
    """ :returns the natural logarithm (base e) of x. """
    n = 50000.0
    return n * ((b ** (1/n)) - 1)


def lg(a):
    """ :returns logarithm of x to the base 10. """
    return ln(a) / ln(10)
