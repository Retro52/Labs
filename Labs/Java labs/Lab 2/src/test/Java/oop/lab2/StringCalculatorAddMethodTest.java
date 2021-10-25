package oop.lab2;

import org.junit.Assert;
import org.junit.Test;

public class StringCalculatorAddMethodTest
{
    @Test
    public void TestStepOne()
    {
        Assert.assertEquals(StringCalculator.Add(""), 0);
        Assert.assertEquals(StringCalculator.Add("1"), 1);
        Assert.assertEquals(StringCalculator.Add("1,2"), 3);
    }
}
