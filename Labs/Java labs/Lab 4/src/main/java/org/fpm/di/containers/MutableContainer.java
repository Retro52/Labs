package org.fpm.di.containers;

import org.fpm.di.enums.InjectedClasses;

import java.util.Map;

public class MutableContainer extends DefaultContainer
{
    public MutableContainer() {super();}
    public MutableContainer(DefaultContainer parent) {super(parent);}
    public MutableContainer(DefaultBinder binder) {super(binder);}

    private MutableContainer(Map<Class<?>, ReturnType> h, DefaultContainer p) {super(h, p);}

    @Override
    protected DefaultContainer Clone(DefaultContainer sample)
    {
        return new MutableContainer(sample.classStorage, sample.parentContainer);
    }

    public ImmutableContainer Immutable() {return (ImmutableContainer) new ImmutableContainer().Clone(this);}

    protected <T> void store(Class<T> key, InjectedClasses mode)
    {
        if (mode == InjectedClasses.SINGLETON)
        {
            classStorage.put(key, new SingletonReturnType(key));
        }
        else if (mode == InjectedClasses.DEFAULT)
        {
            classStorage.put(key, new DefaultReturnType(key));
        }
    }

    protected <T> void store(Class<T> key, Class<? extends T> implementation)
    {
        classStorage.put(key, new PseudonymReturnType(implementation));
    }

    protected <T> void store(Class<T> key, T instance)
    {
        classStorage.put(key, new SingletonReturnType(instance));
    }
}
