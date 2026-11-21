package com.compatibleimgui;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

/** Small reflection helper used by the version-neutral ImGui bridge. */
public final class Reflect {

    private static final Map<String, Field> FIELDS = new ConcurrentHashMap<>();
    private static final Map<String, Method> METHODS = new ConcurrentHashMap<>();

    private Reflect() {
    }

    public static Object get(Object instance, String name) {
        try {
            Class<?> type = instance instanceof Class<?> c ? c : instance.getClass();
            Field field = FIELDS.computeIfAbsent(type.getName() + '#' + name, key -> {
                try {
                    Field f = type.getField(name);
                    f.setAccessible(true);
                    return f;
                } catch (ReflectiveOperationException e) {
                    throw new IllegalStateException(e);
                }
            });
            return field.get(instance instanceof Class<?> ? null : instance);
        } catch (ReflectiveOperationException e) {
            throw new IllegalStateException(e);
        }
    }

    public static long getLong(Object instance, String name) {
        Object value = get(instance, name);
        return value instanceof Number n ? n.longValue() : 0L;
    }

    public static void set(Object instance, String name, Object value) {
        try {
            Class<?> type = instance.getClass();
            Field field = FIELDS.computeIfAbsent(type.getName() + '#' + name, key -> {
                try {
                    Field f = type.getField(name);
                    f.setAccessible(true);
                    return f;
                } catch (ReflectiveOperationException e) {
                    throw new IllegalStateException(e);
                }
            });
            field.set(instance, value);
        } catch (ReflectiveOperationException e) {
            throw new IllegalStateException(e);
        }
    }

    public static Object getDeclared(Object instance, String name) {
        try {
            Class<?> type = instance instanceof Class<?> c ? c : instance.getClass();
            String key = type.getName() + "#declared#" + name;
            Field field = FIELDS.computeIfAbsent(key, k -> {
                try {
                    Field f = type.getDeclaredField(name);
                    f.setAccessible(true);
                    return f;
                } catch (ReflectiveOperationException e) {
                    throw new IllegalStateException(e);
                }
            });
            return field.get(instance instanceof Class<?> ? null : instance);
        } catch (ReflectiveOperationException e) {
            throw new IllegalStateException(e);
        }
    }

    public static Object call(Object instance, String name, Object... args) {
        try {
            Class<?> type = instance instanceof Class<?> c ? c : instance.getClass();
            String key = type.getName() + '#' + name + '#' + args.length;
            Method method = METHODS.computeIfAbsent(key, k -> {
                for (Method m : type.getMethods()) {
                    if (m.getName().equals(name) && m.getParameterCount() == args.length) {
                        m.setAccessible(true);
                        return m;
                    }
                }
                for (Method m : type.getDeclaredMethods()) {
                    if (m.getName().equals(name) && m.getParameterCount() == args.length) {
                        m.setAccessible(true);
                        return m;
                    }
                }
                throw new IllegalStateException("No method " + name + "/" + args.length + " on " + type.getName());
            });
            return method.invoke(instance instanceof Class<?> ? null : instance, args);
        } catch (ReflectiveOperationException e) {
            throw new IllegalStateException(e);
        }
    }

    public static Object construct(Class<?> type, Class<?>[] parameterTypes, Object... args) {
        try {
            var ctor = type.getConstructor(parameterTypes);
            ctor.setAccessible(true);
            return ctor.newInstance(args);
        } catch (ReflectiveOperationException e) {
            throw new IllegalStateException(e);
        }
    }

    public static MethodHandle handle(Method method) {
        try {
            return MethodHandles.lookup().unreflect(method);
        } catch (IllegalAccessException e) {
            throw new IllegalStateException(e);
        }
    }

}
