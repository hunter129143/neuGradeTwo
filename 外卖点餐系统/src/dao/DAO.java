package dao;

import javax.imageio.IIOException;
import java.io.IOException;
import java.util.List;

public interface DAO<T> {
    void insert(T t);
    T findById(String id);
    List<T> findAll();
    void delete(String id);
    void addMessage() throws IOException;
}