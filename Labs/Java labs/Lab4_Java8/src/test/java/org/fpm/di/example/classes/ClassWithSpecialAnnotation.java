package org.fpm.di.example.classes;

import org.fpm.di.annotations.IgnoreAccessModifiers;

import javax.inject.Inject;

public class ClassWithSpecialAnnotation
{
    @Inject
    @IgnoreAccessModifiers
    private ClassWithSpecialAnnotation(){}
}
