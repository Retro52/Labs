package org.fpm.di.example.tests;

import org.fpm.di.containers.DefaultBinder;
import org.fpm.di.containers.ImmutableContainer;
import org.fpm.di.containers.MutableContainer;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class TestMutableExceptions
{
    @Before
    public void SetUp()
    {

    }

    @Test
    public void TestMutableContainerConstructors()
    {
        MutableContainer first = new MutableContainer();
        MutableContainer second = new MutableContainer(first);
        MutableContainer third = new MutableContainer(new DefaultBinder());
    }

    @Test
    public void TestMutableContainerCreators()
    {
        DefaultBinder binder = new DefaultBinder();
        binder.bind(MutableContainer.class);
        MutableContainer A = new MutableContainer(binder);
        ImmutableContainer B = A.Immutable();
        assertEquals(A.getComponent(MutableContainer.class).getClass(), B.getComponent(MutableContainer.class).getClass());
    }
}
