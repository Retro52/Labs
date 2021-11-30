package com.company;

import java.util.Collection;
import java.util.Iterator;

public class Matrix extends AbstractMatrix
{
    // Constructors remain pretty much the same
    public Matrix() { super(); }
    public Matrix(int lines, int columns) { super(lines, columns); }
    public Matrix(AbstractMatrix matrix) { super(matrix); }
    public Matrix(Double[][] matrix) { super(matrix); }

    public static Matrix transpose(Object matrix)
    {
        return (Matrix) AbstractMatrix.transpose(matrix);
    }


    // method to fill matrix using collection of Doubles
    public void fill(Collection<Collection<Double>> values)
    {
        if (values == null)
        {
            throw new RuntimeException("Given matrix is null");
        }
        Iterator<Collection<Double>> line = values.iterator();
        for (int i = 0; i < M; i++)
        {
            SetRowI(i, line.next());
        }
    }

    // method to fill matrix Double[][]
    public void fill(Double[][] values)
    {
        if (values == null)
        {
            throw new RuntimeException("Given matrix is null");
        }
        for (int i = 0; i <= M; i++)
        {
            SetRowI(i, values[i]);
        }
    }

    // setter to set value at i, j spot
    public void SetElement(int i, int j, Double value)
    {
        if (i >= M || j >= N)
        {
            throw new RuntimeException("Illegal index for row or column");
        }
        data[i][j] = value;
    }

    // setter to set i-th row to the given
    public void SetRowI(int i, Double[] row)
    {
        if (row.length != N || i >= M)
        {
            throw new RuntimeException("Illegal column dimension or index is out of range");
        }
        System.arraycopy(row, 0, data[i], 0, N);
    }

    @SuppressWarnings("Duplicates")
    // setter to set i-th row to the given
    public void SetRowI(int i, Collection<Double> row)
    {
        if (row.size() != N || i >= M)
        {
            throw new RuntimeException("Illegal column dimension or index is out of range");
        }
        Iterator<Double> value = row.iterator();
        for (int j = 0; j < N; j++)
        {
            data[i][j] = value.next();
        }
    }

    @SuppressWarnings("Duplicates")
    // setter to set j-th column to the given
    public void SetColumnJ(int j, Collection<Double> column)
    {
        if (column.size() != M || j >= N)
        {
            throw new RuntimeException("Illegal column dimension or index is out of range");
        }
        Iterator<Double> value = column.iterator();
        for (int i = 0; i < M; i++)
        {
            data[i][j] = value.next();
        }
    }

    // setter to set j-th column to the given
    public void SetColumnJ(int j, Double[] column)
    {
        if (column.length != M || j >= N)
        {
            throw new RuntimeException("Illegal column dimension or index is out of range");
        }
        for (int i = 0; i < M; i++)
        {
            this.data[i][j] = column[i];
        }
    }


    public Matrix transpose()
    {
        return (Matrix) AbstractMatrix.transpose(this);
    }

    public void FillRandomColumn(int min, int max)
    {
        AbstractMatrix.FillRandomColumn(this, min, max);
    }

    public static void FillRandomColumn(Matrix matrix, int min, int max)
    {
        AbstractMatrix.FillRandomColumn(matrix, min, max);
    }

    public static Matrix FillRandomColumn(int height, int min, int max)
    {
        Matrix matrix = new Matrix(height, 1);
        AbstractMatrix.FillRandomColumn(matrix, min, max);
        return matrix;
    }
}
