package com.company;

import java.util.Arrays;
import java.util.Collection;
import java.util.Iterator;
import java.util.Objects;

public class AbstractMatrix implements GenericMatrixInterface<Double>
{
    protected final int M;             // number of rows
    protected final int N;             // number of columns
    protected final Double[][] data;   // M-by-N array

    // constructor to create empty matrix 0 by 0
    protected AbstractMatrix()
    {
        this.N = 0;
        this.M = 0;
        this.data = new Double[M][N];
    }

    // copy constructor
    protected AbstractMatrix(AbstractMatrix A)
    {
        if (A == null)
        {
            throw new RuntimeException("Given matrix is null");
        }
        this.M = A.M;
        this.N = A.N;
        this.data = new Double[this.M][this.N];
        for (int i = 0; i < A.M; i++)
        {
            System.arraycopy(A.data[i], 0, this.data[i], 0, A.N);
        }
    }

    // constructor to create matrix from given data
    protected AbstractMatrix(Double[][] source)
    {
        if (source == null)
        {
            throw new RuntimeException("Given matrix is null");
        }
        M = source.length;
        N = source[0].length;
        this.data = new Double[M][N];
        for (int i = 0; i < M; i++)
        {
            System.arraycopy(source[i], 0, this.data[i], 0, N);
        }
    }

    // constructor to create M-by-N matrix of 0's
    protected AbstractMatrix(int M, int N)
    {
        this.M = M;
        this.N = N;
        this.data = new Double[M][N];
        for (Double[] row: this.data)
        {
            Arrays.fill(row, 0.0);
        }
    }

    @Override
    // Returns matrix size
    public int[] size()
    {
        return new int[] {M, N};
    }
    @Override
    // Returns M (rows number)
    public int rows()
    {
        return M;
    }

    @Override
    // Returns N (columns number)
    public int columns()
    {
        return N;
    }

    // debug feature to print matrix values
    public void display()
    {
        for (int i = 0; i < N; i++)
        {
            System.out.print("-----------");
        }
        System.out.println();
        for (int i = 0; i < M; i++)
        {
            System.out.print("|");
            for (int j = 0; j < N; j++)
            {
                System.out.printf("%9.1f ", this.data[i][j]);
            }
            System.out.println("|");
        }
        for (int i = 0; i < N; i++)
        {
            System.out.print("-----------");
        }
        System.out.println();
    }

    @Override
    public Double[][] data()
    {
        return data;
    }

    @Override
    public Double GetElement(int i, int j)
    {
        if (i >= M || j >= N)
        {
            throw new RuntimeException("Illegal index for row or column");
        }
        return data[i][j];
    }

    @Override
    public Double[] GetRowI(int i)
    {
        if (i >= M)
        {
            throw new RuntimeException("Illegal index for row or column");
        }
        return data[i];
    }

    @Override
    public Double[] GetColumnJ(int j)
    {
        if (j >= N)
        {
            throw new RuntimeException("Illegal index for row or column");
        }
        Double[] column = new Double[M];
        for (int i = 0; i < M; i++) column[i] = data[i][j];
        return column;
    }

    @Override
    // returns true if matrices are the same or false, if not
    public boolean equals(Object matrix)
    {
        if (matrix == null)
        {
            return false;
        }
        if (matrix == this)
        {
            return true;
        }
        if (matrix instanceof AbstractMatrix)
        {
            if (((AbstractMatrix) matrix).M != this.M || ((AbstractMatrix) matrix).N != this.N)
            {
                throw new RuntimeException("Matrix dimensions are not the same");
            }

            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (!Objects.equals(this.data[i][j], ((AbstractMatrix) matrix).data[i][j]))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    @Override
    // returns matrix hash code. Tip: same hash codes does not mean that matrices are the same
    public int hashCode()
    {
        return Arrays.deepHashCode(data);
    }

    // This method fills given column with random numbers
    protected static void FillRandomColumn(Object matrix, int min, int max)
    {
        if (!(matrix instanceof AbstractMatrix))
        {
            throw new RuntimeException("Illegal object type passed, matrix or ExtendedMatrix expected");
        }
        if (((AbstractMatrix) matrix).columns() > 1)
        {
            throw new RuntimeException("Given matrix has more than 1 column");
        }
        int delta = max - min + 1;
        for (int i = 0; i < ((AbstractMatrix) matrix).rows(); i++)
        {
            ((AbstractMatrix) matrix).data[i][0] = Math.floor((Math.random() * delta) + min);
        }
    }

    // returns transposed matrix (its static, so takes any matrix as a parameter)
    protected static Object transpose(Object matrix)
    {
        if (matrix instanceof AbstractMatrix)
        {
            int N = ((AbstractMatrix) matrix).N;
            int M = ((AbstractMatrix) matrix).M;
            AbstractMatrix A = new Matrix(N, M);
            if (matrix instanceof ImmutableMatrix)
            {
                A = new ImmutableMatrix(N, M);
            }
            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    A.data[j][i] = ((AbstractMatrix) matrix).data[i][j];
            return A;
        }
        else
        {
            throw new RuntimeException("Illegal object type passed, Matrix or Immutable expected");
        }
    }
}
