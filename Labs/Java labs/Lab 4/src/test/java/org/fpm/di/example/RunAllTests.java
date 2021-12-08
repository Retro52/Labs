package org.fpm.di.example;

import org.fpm.di.example.tests.Example;
import org.fpm.di.example.tests.TestExceptions;
import org.fpm.di.example.tests.TestImmutableContainer;
import org.fpm.di.example.tests.TestMutableExceptions;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;

@RunWith(Suite.class)
@Suite.SuiteClasses({Example.class,
        TestExceptions.class,
        TestImmutableContainer.class,
        TestMutableExceptions.class})
public class RunAllTests {}
