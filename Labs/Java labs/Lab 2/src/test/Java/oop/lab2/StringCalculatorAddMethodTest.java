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

    @Test
    public void TestStepTwo()
    {
        Assert.assertEquals(StringCalculator.Add("1,2,3,4"), 10);
        Assert.assertEquals(StringCalculator.Add("12,5,300"), 317);
        Assert.assertEquals(StringCalculator.Add("96,69,96,69,96,69,96,69"), 660);
    }
}
