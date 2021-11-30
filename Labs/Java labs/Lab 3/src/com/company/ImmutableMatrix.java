package com.company;

public final class ImmutableMatrix extends AbstractMatrix
{
    // Constructors remain pretty much the same
    public ImmutableMatrix() { super(); }
    public ImmutableMatrix(int lines, int columns) { super(lines, columns); }
    public ImmutableMatrix(AbstractMatrix matrix) { super(matrix); }
    public ImmutableMatrix(Double[][] matrix) { super(matrix); }

    // All we need to change - static methods
    public static ImmutableMatrix CreateRandomColumn(int len, int min, int max)
    {
        ImmutableMatrix result = new ImmutableMatrix(len, 1);
        FillRandomColumn(result, min, max);
        return result;
    }

    public ImmutableMatrix transpose()
    {
        return (ImmutableMatrix) AbstractMatrix.transpose(this);
    }

    public static ImmutableMatrix transpose(Object matrix)
    {
        return (ImmutableMatrix) AbstractMatrix.transpose(matrix);
    }
}
