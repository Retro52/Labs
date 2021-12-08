package org.fpm.di.containers;

import java.util.Map;

public final class ImmutableContainer extends DefaultContainer
{
    public ImmutableContainer() {super();}
    public ImmutableContainer(DefaultContainer parent) {super(parent);}
    public ImmutableContainer(DefaultBinder binder) {super(binder);}

    private ImmutableContainer( Map<Class<?>, ReturnType> h, DefaultContainer p) {super(h, p);}

    @Override
    protected DefaultContainer Clone(DefaultContainer sample)
    {
        return new ImmutableContainer(sample.classStorage, sample.parentContainer);
    }


    public MutableContainer Mutable() {return (MutableContainer) new MutableContainer().Clone(this);}
}
