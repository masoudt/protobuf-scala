As opposed to conventional protobuf code, the messages are written in a tree form inferred from the schema definition:
```
message Artist {
  required string name = 1;
  message Album {
    required string title = 1;
    repeated string tracks = 2;
    optional uint32 year_produced = 3;
  }

  repeated Album albums = 2;
}

val BradMehldau = Artist (
  name("Brad Mehldau"),
  albums (
    Album (
      title("Day Is Done"),
      tracks(
        "50 ways to leave your lover",
        "Grenada"
      ),
      year_produced(2005)
    )
  )
)
```
Compare this with Java spaghetti code needed to encode the same message.