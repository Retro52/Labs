package org.fpm.di.containers;


import org.fpm.di.Configuration;
import org.fpm.di.Environment;

public class DefaultEnvironment implements Environment
{
    @Override
    public MutableContainer configure(Configuration configuration)
    {
        MutableContainer container = new MutableContainer();
        configuration.configure(new DefaultBinder(container));
        return container;
    }
}
