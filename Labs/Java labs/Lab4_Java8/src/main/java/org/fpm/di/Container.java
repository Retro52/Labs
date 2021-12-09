package org.fpm.di;

public interface Container
{
    <T> T getComponent(Class<T> clazz);
}
