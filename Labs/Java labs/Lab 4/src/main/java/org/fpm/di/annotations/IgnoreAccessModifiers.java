package org.fpm.di.annotations;

import javax.inject.Scope;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.Target;

import static java.lang.annotation.RetentionPolicy.RUNTIME;

@Scope
@Target(ElementType.CONSTRUCTOR)
@Retention(RUNTIME)
/* Adding this annotation to constructor makes container ignore constructor access modifiers inject it anyway
* Of course, you still need to add @Inject annotation to this constructor */
public @interface IgnoreAccessModifiers {}
