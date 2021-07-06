import getopt, sys

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "vhL:", ["version", "help", "loglevel"])
    except getopt.GetoptError as e:
        print(e)
        sys.exit(1)
    
    loglevel = "WARN"
    for o, a in opts:
        if o in ["-v", "--version"]:
            print("1.0.0")
            sys.exit(0)
        elif o in ["-h", "--help"]:
            print("Testing getopt module.")
            sys.exit(0)
        elif o in ["-L", "--loglevel"]:
            if a.upper() in ["ERROR", "WARN", "NOTICE", "INFO", "DEBUG"]:
                loglevel = a.upper()
            else:
                print("Invalid loglevel")
                sys.exit(1)


if __name__ == "__main__":
    main()
