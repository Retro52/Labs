package org.fpm.di.containers;

import org.fpm.di.Container;
import org.fpm.di.annotations.IgnoreAccessModifiers;
import org.fpm.di.exceptions.ClassConstructorsHaveIllegalArguments;
import org.fpm.di.exceptions.ContainerHasNoAccessibleConstructorsException;
import org.fpm.di.exceptions.ContainerInternalException;
import org.fpm.di.exceptions.ContainerReturnNotRegisteredException;

import javax.inject.Inject;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.*;


public abstract class DefaultContainer implements Container
{
    protected final Map<Class<?>, ReturnType> classStorage;
    protected final DefaultContainer parentContainer;


    protected ReturnType GetValueByKey(Class<?> clazz)
    {
        if (classStorage.containsKey(clazz))
        {
            return classStorage.get(clazz);
        }
        else if (parentContainer != null && parentContainer.ContainsNecessaryClass(clazz))
        {
            return parentContainer.GetValueByKey(clazz);
        }
        else throw new ContainerReturnNotRegisteredException(clazz);
    }

    protected boolean ContainsNecessaryClass(Class<?> clazz)
    {
        return classStorage.containsKey(clazz) || (parentContainer != null && parentContainer.ContainsNecessaryClass(clazz));
    }

    protected boolean ContainsAllNecessaryClasses(Class<?>[] clazzes)
    {
        for (Class<?> clazz: clazzes)
        {
            if (!ContainsNecessaryClass(clazz))
            {
                return false;
            }
        }
        return true;
    }


    protected DefaultContainer()
    {
        classStorage = Collections.synchronizedMap(new HashMap<>());
        parentContainer = null;
    }

    protected DefaultContainer(DefaultBinder binder)
    {
        MutableContainer cloningContainer = binder.getContainer();
        classStorage = cloningContainer.classStorage;
        parentContainer = cloningContainer.parentContainer;
    }

    protected DefaultContainer(DefaultContainer parent)
    {
        classStorage = Collections.synchronizedMap(new HashMap<>());
        parentContainer = parent;
    }

    protected DefaultContainer(Map<Class<?>, ReturnType> h, DefaultContainer parentContainer)
    {
        classStorage = h;
        this.parentContainer = parentContainer;
    }

    protected abstract DefaultContainer Clone(DefaultContainer sample);

    @SuppressWarnings("unchecked")
    @Override
    public <T> T getComponent(Class<T> clazz)
    {
        try
        {
            return (T) GetValueByKey(clazz).getInstance();
        }
        catch (ClassCastException exception)
        {
            throw new RuntimeException("Unexpected ClassCastException");
        }
    }

    abstract static class ReturnType
    {
        abstract Object getInstance();
    }

    class PseudonymReturnType extends ReturnType
    {
        Class<?> target;

        PseudonymReturnType(Class<?> clazz)
        {
            target = clazz;
        }

        Object getInstance()
        {
            return GetValueByKey(target).getInstance();
        }
    }

    class DefaultReturnType extends ReturnType
    {
        private final ArrayList<Constructor<?>> injectionConstructors;

        private void insertConstructor(Constructor<?> constructor)
        {
            if (constructor.canAccess(null))
            {
                injectionConstructors.add(constructor);
            }
            else if(constructor.isAnnotationPresent(IgnoreAccessModifiers.class))
            {
                if (constructor.trySetAccessible())
                {
                    injectionConstructors.add(constructor);
                }
            }
            else if(!constructor.canAccess(null))
            {
                System.err.println("Warning: @Inject annotation found on Constructor " + constructor + ", which does not have @IgnoreAccessModifiers annotation on it");
            }
        }

        DefaultReturnType()
        {
            injectionConstructors = null;
        }

        DefaultReturnType(Class<?> clazz)
        {
            injectionConstructors = new ArrayList<>();
            Constructor<?>[] constructors = clazz.getConstructors();
            if (constructors.length == 1) insertConstructor(constructors[0]);
            else
            {
                for (Constructor<?> constructor : constructors)
                {
                    if (constructor.isAnnotationPresent(Inject.class)) insertConstructor(constructor);
                }

                if (injectionConstructors.size() == 0)
                {
                    for (Constructor<?> constructor : constructors)
                    {
                        if (constructor.getParameterCount() == 0) insertConstructor(constructor);
                    }

                    if (injectionConstructors.size() == 0)
                    {
                        throw new ContainerHasNoAccessibleConstructorsException(clazz);
                    }
                }
            }
        }

        @Override
        Object getInstance()
        {
            for (Constructor<?> constructor: injectionConstructors)
            {
                try
                {
                    if (ContainsAllNecessaryClasses(constructor.getParameterTypes()))
                    {
                        if (constructor.getParameterCount() > 0)
                        {
                            Class<?>[] types = constructor.getParameterTypes();
                            Object[] args = new Object[types.length];
                            for (int i = 0; i < types.length; i++)
                            {
                                args[i] = GetValueByKey(types[i]).getInstance();
                            }
                            return constructor.newInstance(args);
                        }
                        else
                        {
                            return constructor.newInstance();
                        }
                    }
                }
                catch (InvocationTargetException | InstantiationException | IllegalAccessException exception)
                {
                    throw new ContainerInternalException();
                }
            }
            throw new ClassConstructorsHaveIllegalArguments(injectionConstructors);
        }
    }

    class SingletonReturnType extends DefaultReturnType
    {
        private Object returnInstance;

        protected SingletonReturnType(Object instance)
        {
            returnInstance = instance;
        }

        protected SingletonReturnType(Class<?> clazz)
        {
            super(clazz);
            returnInstance = null;
        }

        protected Object getInstance()
        {
            if (returnInstance == null)
            {
                returnInstance = super.getInstance();
            }
            return returnInstance;
        }
    }
}