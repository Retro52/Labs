package org.fpm.di.containers;


import org.fpm.di.Binder;
import org.fpm.di.enums.InjectedClasses;

import javax.inject.Singleton;



public class DefaultBinder implements Binder
{
    private final MutableContainer container;
    public MutableContainer getContainer()
    {
        return container;
    }


    public DefaultBinder()
    {
        container = new MutableContainer();
    }

    public DefaultBinder(MutableContainer bindingContainer)
    {
        this.container = bindingContainer;
    }


    @Override
    public <T> void bind(Class<T> clazz)
    {
        if (clazz.isAnnotationPresent(Singleton.class))
        {
            container.store(clazz, InjectedClasses.SINGLETON);
        }
        else
        {
            container.store(clazz, InjectedClasses.DEFAULT);
        }
    }

    @Override
    public <T> void bind(Class<T> clazz, Class<? extends T> implementation)
    {
        container.store(clazz, implementation);
    }

    @Override
    public <T> void bind(Class<T> clazz, T instance)
    {
        container.store(clazz, instance);
    }
}
