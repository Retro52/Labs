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

    @Test
    public void TestStepThree()
    {
        Assert.assertEquals(StringCalculator.Add("1,2"), 3);
        Assert.assertEquals(StringCalculator.Add("1\n2\n3"), 6);
        Assert.assertEquals(StringCalculator.Add("1\n3,5"), 9);
    }

    @Test
    public void TestStepFour()
    {
        Assert.assertEquals(StringCalculator.Add("//;\n1;2;3"), 6);
        Assert.assertEquals(StringCalculator.Add("//;\n123"), 123);
        Assert.assertEquals(StringCalculator.Add("//;\n"),0);
    }
}
