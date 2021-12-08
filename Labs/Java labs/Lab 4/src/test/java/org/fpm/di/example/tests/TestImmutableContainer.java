package org.fpm.di.example.tests;

import org.fpm.di.containers.DefaultBinder;
import org.fpm.di.containers.ImmutableContainer;
import org.fpm.di.containers.MutableContainer;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class TestImmutableContainer
{
    @Before
    public void SetUp()
    {

    }

    @Test
    public void TestImmutableContainerConstructors()
    {
        ImmutableContainer first = new ImmutableContainer();
        ImmutableContainer second = new ImmutableContainer(first);
        ImmutableContainer third = new ImmutableContainer(new DefaultBinder());
    }

    @Test
    public void TestImmutableContainerCreators()
    {
        DefaultBinder binder = new DefaultBinder();
        binder.bind(ImmutableContainer.class);
        ImmutableContainer A = new ImmutableContainer(binder);
        MutableContainer B = A.Mutable();
        assertEquals(A.getComponent(ImmutableContainer.class).getClass(), B.getComponent(ImmutableContainer.class).getClass());
    }
}
