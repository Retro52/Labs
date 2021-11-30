package com.company;

public class Main
{

    public static void main(String[] args)
    {
        Matrix A = new Matrix(10, 2);
        A.display();
        A.SetElement(0, 0, 10.0);
        A.display();
        ImmutableMatrix B = new ImmutableMatrix(A);
        B.display();
        Matrix a = new Matrix(10, 1);
        ImmutableMatrix.FillRandomColumn(a, 0, (int) Math.E);
        a.display();
    }
}

