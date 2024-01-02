import os
from argparse import ArgumentParser


def make_parser():
    parser = ArgumentParser(description="Define the parameters")

    parser.add_argument('-d', type=str, required=False, 
                        help='The root directory where the exploration starts. If unspecified, will use ./'
                        )

    parser.add_argument('-maxdepth', type=int, required=False, 
                        help='How many directory deep the program will descend.'
                        )

    parser.set_defaults(d='./', maxdepth=-1)

    return parser


def listDir(root, maxDepth):
    stack = [ root ]
    level = [ 0 ]
    
    # Iteratively listing directories
    while stack:
        currentFile  = stack.pop()
        currentDepth = level.pop()

        if maxDepth != -1 and currentDepth > maxDepth:
            continue

        print(f"❘{'――'*currentDepth}| {currentFile.split('/')[-1]}")

        if os.path.isdir(currentFile):
            subFiles = [os.path.join(currentFile, file) for file in os.listdir(currentFile)]
            
            for sub in subFiles:
                stack.append(sub)
                level.append(currentDepth+1)


def main():
    args     = make_parser().parse_args()
    MAXDEPTH = args.maxdepth
    ROOT     = args.d

    listDir(ROOT, MAXDEPTH)


if __name__ == '__main__':
    main()