package org.fpm.di;

public interface Binder
{
    <T> void bind(Class<T> clazz);

    <T> void bind(Class<T> clazz, Class<? extends T> implementation);

    <T> void bind(Class<T> clazz, T instance);
}


