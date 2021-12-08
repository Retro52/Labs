package org.fpm.di.example.classes;

import org.fpm.di.Configuration;
import org.fpm.di.Container;
import org.fpm.di.Environment;

public class DummyEnvironment implements Environment
{

    @Override
    public Container configure(Configuration configuration) {
        return new DummyContainer();
    }
}
