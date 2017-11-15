import scala.collection.mutable

object Main extends App {

  val graphs = new SimpleGraph[String](
    Map(
      "A" -> Map("B" -> 7, "C" -> 8),
      "B" -> Map("A" -> 7, "F" -> 2),
      "C" -> Map("A" -> 8, "G" -> 4, "F" -> 6),
      "D" -> Map("F" -> 8),
      "E" -> Map("H" -> 1),
      "F" -> Map("B" -> 2, "C" -> 6, "D" -> 8, "G" -> 9, "H" -> 1),
      "G" -> Map("C" -> 4, "F" -> 9),
      "H" -> Map("E" -> 1, "F" -> 3)
    )
  )
  graphs.getShortestPath("A","E")

}

case class SimpleGraph[N](succs: Map[N, Map[N, Int]]) {

  def apply(n: N) = succs.getOrElse(n, Map.empty)

  def initDistance(point:N) = {
    this.succs.foldLeft(Map.empty:Map[N, (Int, Seq[N])]) {
      (result, vertex) =>
        if (vertex._1 == point) {
          result ++ Map(point -> (0,Seq(point)))
        } else {
          result ++ Map(vertex._1 -> (Int.MaxValue, Seq(point)))
        }
    }
  }

  def shortestPath(n:N)(selected:Set[N])(currentDistance:Map[N, (Int, Seq[N])]) = {
    currentDistance.keys.filterNot(selected.contains(_)).foldLeft(n:N) {
      (result, point) =>
        currentDistance(point)._1 match {
          case x if result == n => point
          case y if (currentDistance(result)._1 > y) => point
          case _ => result
        }
    }
  }

  def updateGraph(n:N)(f:N)(distance:Map[N, (Int, Seq[N])]):Map[N, (Int, Seq[N])] = {
    val hereDistance = distance(f)
    this.succs(f).foldLeft(distance:Map[N, (Int, Seq[N])]) {
      (result, vertex) =>
        val nodeDistance = hereDistance._1 match {
          case Int.MaxValue => vertex._2
          case _ => hereDistance._1 + vertex._2
        }
        if (distance(vertex._1)._1 > nodeDistance) {
          result ++ Map(vertex._1 -> (nodeDistance, hereDistance._2 :+ vertex._1))
        } else {
          result
        }
    }
  }

  def getShortestPath(start: N, finish: N) = {
    var nextNode:N = start;
    var currentDistance:Map[N, (Int, Seq[N])] = initDistance(start);
    var unreachedVertexSet:Set[N] = succs.keySet.filterNot(_ == start)
    while (!unreachedVertexSet.isEmpty) {
      currentDistance = updateGraph(start)(nextNode)(currentDistance)
      nextNode = shortestPath(start)(succs.keySet.filterNot(unreachedVertexSet.contains(_)))(currentDistance)
      unreachedVertexSet = unreachedVertexSet.-(nextNode)
    }
    println(currentDistance(finish)._2.reverse.toSeq)
  }

}