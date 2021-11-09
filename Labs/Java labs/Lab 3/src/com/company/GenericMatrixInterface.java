package com.company;

import java.util.Collection;

public interface GenericMatrixInterface <T>
{
        int[] size();
        int rows();
        int columns();

        T[][] data();

        T GetElement(int line, int column);
        T[] GetRowI(int index);
        T[] GetColumnJ(int index);
}
