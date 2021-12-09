package org.fpm.di.example;

import org.fpm.di.example.tests.*;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;

@RunWith(Suite.class)
@Suite.SuiteClasses({Example.class,
        TestExceptions.class,
        TestImmutableContainer.class,
        TestMutableExceptions.class,
        TestAnnotation.class})
public class RunAllTests {}
