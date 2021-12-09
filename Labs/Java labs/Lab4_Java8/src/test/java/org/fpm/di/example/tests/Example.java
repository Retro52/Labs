package org.fpm.di.example.tests;

import org.fpm.di.Container;
import org.fpm.di.Environment;
import org.fpm.di.containers.DefaultEnvironment;
import org.fpm.di.example.MyConfiguration;
import org.fpm.di.example.classes.*;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertNotSame;
import static org.junit.Assert.assertSame;

public class Example
{

    private Container container;

    @Before
    public void setUp()
    {
        Environment env = new DefaultEnvironment();
        container = env.configure(new MyConfiguration());
    }

    @Test
    public void shouldInjectSingleton()
    {
        assertSame(container.getComponent(MySingleton.class), container.getComponent(MySingleton.class));
    }

    @Test
    public void shouldInjectPrototype()
    {
        assertNotSame(container.getComponent(MyPrototype.class), container.getComponent(MyPrototype.class));
    }

    @Test
    public void shouldBuildInjectionGraph()
    {
        /*
        binder.bind(A.class, B.class);
        binder.bind(B.class, new B());
        */
        final B bAsSingleton = container.getComponent(B.class);
        assertSame(container.getComponent(A.class), bAsSingleton);
        assertSame(container.getComponent(B.class), bAsSingleton);
    }

    @Test
    public void shouldBuildInjectDependencies()
    {
        final UseA hasADependency = container.getComponent(UseA.class);
        assertSame(hasADependency.getDependency(), container.getComponent(B.class));
    }

    //
    //    public void shouldThrowContainerHasNoAccessibleConstructorsException()
    //    {
    //        assertThat(IllegalArgumentException.class, () -> StringCalculator.Add("//;\n-1;-5;-7"));
    //        assertEquals("Negatives not allowed [-1; -5; -7]", exception.getMessage());
    //    }
}
