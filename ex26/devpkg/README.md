## Options

- `-I [URL]`: Install software from the provided URL.
- `-L`: List installed software.
- `-c [options]`: Set configuration options for installation.
- `-m [options]`: Set make options for building.
- `-i [options]`: Set install options.
- `-S`: Initialize the database.
- `-F [URL]`: Fetch software from the provided URL.
- `-B [URL]`: Build software from the provided URL.

## Example
To install a software package from a URL, use the following command:
```
./devpkg -I http://example.com/package.tar.gz -c "configure options" -m "make options" -i "install options"
```

